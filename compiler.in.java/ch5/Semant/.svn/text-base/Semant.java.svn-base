/*
 * Semant.java - Semantic analysis
 *
 * Time-stamp: <2010-06-28 13:31:21 wbb>
 */

package Semant;
import Translate.Exp;
import Symbol.Table;

class Env {
    Table venv;                 // value environment
    Table tenv;                 // type environment
    ErrorMsg.ErrorMsg errorMsg;
    
    Env(ErrorMsg.ErrorMsg err) {
        errorMsg = err;
        venv = new Table();
        tenv = new Table();

        /*
         * Initialize the environment.
         */
        
        // print(s: string)
        venv.put(Symbol.Symbol.symbol("print"),
                 new FunEntry(new Types.RECORD(Symbol.Symbol.symbol("s"), new Types.STRING(), null), new Types.VOID()));

        // flush()
        venv.put(Symbol.Symbol.symbol("flush"),
                 new FunEntry(null, new Types.VOID()));

        tenv.put(Symbol.Symbol.symbol("int"), new Types.INT());
        tenv.put(Symbol.Symbol.symbol("string"), new Types.STRING());
    }
}


abstract class Entry { }

class VarEntry extends Entry {
    Types.Type ty;
    VarEntry(Types.Type t) {
        ty = t;
    }
}


class FunEntry extends Entry {
    Types.RECORD formals;
    Types.Type result;
    public FunEntry(Types.RECORD f, Types.Type r) {
        formals = f;
        result = r;
    }
}


public class Semant {
    Env env;

    /*
     * In for-exp or while-exp? To test whether break-exp valid.
     * Only can be manipulated by transExp(Absyn.ForExp) and
     * transExp(Absyn.WhileExp), and test by transExp(Absyn.BreakExp).
     */
    boolean isIteration = false;
    
    public Semant(ErrorMsg.ErrorMsg err) {
        this(new Env(err));
    }

    Semant(Env e) {
        env = e;
    }

    private void error(int pos, String str) {
        env.errorMsg.error(pos, str);
    }
    
    public void transProg(Absyn.Exp exp) {
        transExp(exp);
    }

    ExpTy transVar(Absyn.Var v) {
        if (v instanceof Absyn.SimpleVar) {
            return transVar((Absyn.SimpleVar) v);
        }
        if (v instanceof Absyn.FieldVar) {
            return transVar((Absyn.FieldVar) v);
        }
        if (v instanceof Absyn.SubscriptVar) {
            return transVar((Absyn.SubscriptVar) v);
        }
        throw new Error("transVar");
    }

    ExpTy transVar(Absyn.SimpleVar v) {
        Entry x = (Entry) env.venv.get(v.name);
        if (x instanceof VarEntry) {
            VarEntry ent = (VarEntry) x;
            return new ExpTy(null, ent.ty.actual());
        } else {
            error(v.pos, "undefined variable: " + v.name);
            return new ExpTy(null, new Types.INT());
        }
    }

    ExpTy transVar(Absyn.FieldVar v) {
        ExpTy vt = transVar(v.var);
        if (vt.ty.actual() instanceof Types.RECORD) {
            Types.RECORD ty = (Types.RECORD) vt.ty.actual();
            for (; ty != null; ty = ty.tail) {
                if (ty.fieldName == v.field) {
                    return new ExpTy(null, ty.fieldType.actual());
                }
            }
            error(v.pos, "undefined field: " + v.field);
        } else {
            error(v.pos, "record type required");
        }
        return new ExpTy(null, new Types.INT());

    }

    ExpTy transVar(Absyn.SubscriptVar v) {
        ExpTy vt = transVar(v.var);
        if (vt.ty.actual() instanceof Types.ARRAY) {
            return new ExpTy(null, ((Types.ARRAY)vt.ty.actual()).element);
        } else {
            error(v.pos, "not an array");
            return new ExpTy(null, new Types.INT());
        }
    }
    
    ExpTy transExp(Absyn.Exp e) {
        if (e instanceof Absyn.VarExp) {
            return transExp((Absyn.VarExp) e);
        }
        if (e instanceof Absyn.NilExp) {
            return transExp((Absyn.NilExp) e);
        }
        if (e instanceof Absyn.IntExp) {
            return transExp((Absyn.IntExp) e);
        }
        if (e instanceof Absyn.StringExp) {
            return transExp((Absyn.StringExp) e);
        }
        if (e instanceof Absyn.CallExp) {
            return transExp((Absyn.CallExp) e);
        }
        if (e instanceof Absyn.OpExp) {
            return transExp((Absyn.OpExp) e);
        }
        if (e instanceof Absyn.RecordExp) {
            return transExp((Absyn.RecordExp) e);
        }
        if (e instanceof Absyn.SeqExp) {
            return transExp((Absyn.SeqExp) e);
        }
        if (e instanceof Absyn.AssignExp) {
            return transExp((Absyn.AssignExp) e);
        }
        if (e instanceof Absyn.IfExp) {
            return transExp((Absyn.IfExp) e);
        }
        if (e instanceof Absyn.WhileExp) {
            return transExp((Absyn.WhileExp) e);
        }
        if (e instanceof Absyn.ForExp) {
            return transExp((Absyn.ForExp) e);
        }
        if (e instanceof Absyn.BreakExp) {
            return transExp((Absyn.BreakExp) e);
        }
        if (e instanceof Absyn.LetExp) {
            return transExp((Absyn.LetExp) e);
        }
        if (e instanceof Absyn.ArrayExp) {
            return transExp((Absyn.ArrayExp) e);
        }
        throw new Error("transExp");
    }

    ExpTy transExp(Absyn.VarExp e) {
        return transVar(e.var);
    }

    ExpTy transExp(Absyn.NilExp e) {
        return new ExpTy(null, new Types.NIL());
    }

    ExpTy transExp(Absyn.IntExp e) {
        return new ExpTy(null, new Types.INT());
    }

    ExpTy transExp(Absyn.StringExp e) {
        return new ExpTy(null, new Types.STRING());
    }

    ExpTy transExp(Absyn.CallExp e) {
        Entry x = (Entry) env.venv.get(e.func);
        if (x instanceof FunEntry) {
            FunEntry xx = (FunEntry) x;
            Types.RECORD params = xx.formals;
            Absyn.ExpList args = e.args;
            int n = 0;          // track #parameters

            for (; params != null && args != null;
                 params = params.tail, args = args.tail, n++) {
                ExpTy et = transExp(args.head);
                if (!params.fieldType.coerceTo(et.ty)) {
                    String msg = (n+1) + "th argument type incompatible";
                    error(e.pos, msg);
                }
            }
            if (params != null || args != null) {
                for (; params != null; params = params.tail)
                    n++;
                error(e.pos, "#arguments not matched; " +
                      n + " argument(s) expected");
            }
            return new ExpTy(null, xx.result);
        } else {
            error(e.pos, "undefined function: " + e.func);
            return new ExpTy(null, new Types.INT());
        }
    }

    ExpTy transExp(Absyn.OpExp e) {
        ExpTy left = transExp(e.left);
        ExpTy right = transExp(e.right);
        switch (e.oper) {
        case Absyn.OpExp.PLUS:
            checkInt(left, e.left.pos);
            checkInt(right, e.right.pos);
            return new ExpTy(null, new Types.INT());
        case Absyn.OpExp.MINUS:
            checkInt(left, e.left.pos);
            checkInt(right, e.right.pos);
            return new ExpTy(null, new Types.INT());
        case Absyn.OpExp.MUL:
            checkInt(left, e.left.pos);
            checkInt(right, e.right.pos);
            return new ExpTy(null, new Types.INT());
        case Absyn.OpExp.DIV:
            checkInt(left, e.left.pos);
            checkInt(right, e.right.pos);
            return new ExpTy(null, new Types.INT());
        case Absyn.OpExp.EQ:
            if ((left.ty instanceof Types.INT && right.ty instanceof Types.INT) ||
                (left.ty instanceof Types.STRING && right.ty instanceof Types.STRING))
                return new ExpTy(null, new Types.INT());
            else {
                error(e.pos, "operand not matched");
                break;
            }
        case Absyn.OpExp.NE:
            if ((left.ty instanceof Types.INT && right.ty instanceof Types.INT) ||
                (left.ty instanceof Types.STRING && right.ty instanceof Types.STRING))
                return new ExpTy(null, new Types.INT());
            else {
                error(e.pos, "operand not matched");
                break;
            }
        case Absyn.OpExp.LT:
            if ((left.ty instanceof Types.INT && right.ty instanceof Types.INT) ||
                (left.ty instanceof Types.STRING && right.ty instanceof Types.STRING))
                return new ExpTy(null, new Types.INT());
            else {
                error(e.pos, "operand not matched");
                break;
            }
        case Absyn.OpExp.LE:
            if ((left.ty instanceof Types.INT && right.ty instanceof Types.INT) ||
                (left.ty instanceof Types.STRING && right.ty instanceof Types.STRING))
                return new ExpTy(null, new Types.INT());
            else {
                error(e.pos, "operand not matched");
                break;
            }
        case Absyn.OpExp.GT:
            if ((left.ty instanceof Types.INT && right.ty instanceof Types.INT) ||
                (left.ty instanceof Types.STRING && right.ty instanceof Types.STRING))
                return new ExpTy(null, new Types.INT());
            else {
                error(e.pos, "operand not matched");
                break;
            }
        case Absyn.OpExp.GE:
            if ((left.ty instanceof Types.INT && right.ty instanceof Types.INT) ||
                (left.ty instanceof Types.STRING && right.ty instanceof Types.STRING))
                return new ExpTy(null, new Types.INT());
            else {
                error(e.pos, "operand not matched");
                break;
            }
        default:
            throw new Error("transOpExp");
        }
        return new ExpTy(null, new Types.INT());
    }

    ExpTy transExp(Absyn.RecordExp e) {
        Types.Type ty = ((Types.Type) env.tenv.get(e.typ)).actual();
        if (ty instanceof Types.RECORD) {
            Types.RECORD rd = (Types.RECORD) ty;
            Absyn.FieldExpList fl = e.fields;
            for ( ; rd != null && fl != null; rd = rd.tail, fl = fl.tail) {
                Types.Type init_ty = transExp(fl.init).ty;
                if ((fl.name == rd.fieldName) &&
                    ((rd.fieldType.coerceTo(init_ty)) ||
                     init_ty instanceof Types.NIL)) {
                    continue;
                } else
                    error(fl.pos, "undefined field: " + fl.name +
                          "; '" + rd.fieldName + "' expected");
            }
            if (rd != null || fl != null)
                error(e.pos, "# fields not matched");
            return new ExpTy(null, (Types.RECORD) ty);
        } else {
            error(e.pos, "record type required");
            return new ExpTy(null, new Types.RECORD(e.typ, null, null));
        }
    }

    ExpTy transExp(Absyn.SeqExp e) {
        Absyn.ExpList el = e.list;
        ExpTy et = null;
        while (el != null) {
            et = transExp(el.head);
            el = el.tail;
        }
        if (et == null)
            return new ExpTy(null, new Types.VOID());
        else
            return et;
    }

    ExpTy transExp(Absyn.AssignExp e) {
        ExpTy var_et = transVar(e.var);
        ExpTy exp_et = transExp(e.exp);
        if (exp_et.ty.coerceTo(var_et.ty))
            return new ExpTy(null, exp_et.ty);
        else {
            error(e.pos, "type not matched");
            return new ExpTy(null, exp_et.ty);
        }
    }

    ExpTy transExp(Absyn.IfExp e) {
        ExpTy et1 = transExp(e.test);
        if (! (et1.ty instanceof Types.INT))
            error(e.test.pos, "integer required");

        ExpTy et2 = transExp(e.thenclause);
        ExpTy et3 = null;
        if (e.elseclause != null)
            et3 = transExp(e.elseclause);
        if (et3 != null && ! et2.ty.coerceTo(et3.ty) && ! et3.ty.coerceTo(et2.ty))
            error(e.pos, "type of thenclause and elseclause not matched");
        if (et3 == null)
            return new ExpTy(null, new Types.VOID());
        else
            return new ExpTy(null, et2.ty);
    }

    ExpTy transExp(Absyn.WhileExp e) {
        ExpTy et1 = transExp(e.test);
        boolean iter_save = isIteration;
        isIteration = true;
        ExpTy et2 = transExp(e.body);
        isIteration = iter_save;
        if (! (et1.ty instanceof Types.INT))
            error(e.test.pos, "integer required");
        if (! (et2.ty instanceof Types.VOID))
            error(e.body.pos, "void type required");
        return new ExpTy(null, new Types.VOID());
    }

    ExpTy transExp(Absyn.ForExp e) {
        env.venv.beginScope();
        transDec(e.var);

        ExpTy hi_et = transExp(e.hi);
        VarEntry vent = (VarEntry) env.venv.get(e.var.name);
        if (! hi_et.ty.coerceTo(vent.ty))
            error(e.hi.pos, "type not matched");

        boolean iter_save = isIteration;
        isIteration = true;
        ExpTy body_et = transExp(e.body);
        isIteration = iter_save;
        if (! (body_et.ty instanceof Types.VOID))
            error(e.body.pos, "VOID type required for for expression");

        env.venv.endScope();
        
        return new ExpTy(null, new Types.VOID());
    }

    ExpTy transExp(Absyn.BreakExp e) {
        if (!isIteration)
            error(e.pos, "invalid break-exp; not in a for-exp or while-exp");
        return new ExpTy(null, new Types.VOID());
    }

    ExpTy transExp(Absyn.LetExp e) {
        env.venv.beginScope();
        env.tenv.beginScope();
        for (Absyn.DecList p = e.decs; p != null; p = p.tail)
            transDec(p.head);
        ExpTy et = transExp(e.body);
        env.venv.endScope();
        env.tenv.endScope();
        return new ExpTy(null, et.ty);
    }

    ExpTy transExp(Absyn.ArrayExp e) {
        Types.Type ty = (Types.Type)  env.tenv.get(e.typ);
        if (ty == null) {
            error(e.pos, "undefined array type: " + e.typ);
            return new ExpTy(null, new Types.ARRAY(new Types.INT()));
        }
        if (! (ty.actual() instanceof Types.ARRAY)) {
            error(e.pos, "ARRAY required");
            return new ExpTy(null, new Types.ARRAY(new Types.INT()));
        }
        
        Types.ARRAY array_ty = (Types.ARRAY) ty.actual();
        if (! (transExp(e.size).ty instanceof Types.INT)) {
            error(e.size.pos, "integer required");
            return new ExpTy(null, new Types.ARRAY(new Types.INT()));
        }
        if (! transExp(e.init).ty.coerceTo(array_ty.element)) {
            error(e.init.pos, "incompatible with array type");
            return new ExpTy(null, new Types.ARRAY(new Types.INT()));
        }
        return new ExpTy(null, array_ty);
    }

    Exp transDec(Absyn.Dec e) {
        if (e instanceof Absyn.FunctionDec)
            return transDec((Absyn.FunctionDec) e);
        if (e instanceof Absyn.VarDec)
            return transDec((Absyn.VarDec) e);
        if (e instanceof Absyn.TypeDec)
            return transDec((Absyn.TypeDec) e);
        throw new Error("transDec");
    }

    Exp transDec(Absyn.FunctionDec d) {
        for (Absyn.FunctionDec p = d, pre = null; p != null; p = p.next) {
            if (env.venv.isRedefinition(p.name)) {
                error(p.pos, "function redefinition of '" + p.name + "'");
                pre.next = p.next; // skip this redefinition
            } else {
                Types.Type result = transTy(p.result);
                Types.RECORD formals = transTypeFields(p.params);
                env.venv.put(p.name, new FunEntry(formals, result));
                pre = p;
            }
        }
        
        for (; d != null; d = d.next) {
            Types.RECORD formals = transTypeFields(d.params);
            env.venv.beginScope();
            for (Types.RECORD r = formals; r != null; r = r.tail) {
                env.venv.put(r.fieldName, new VarEntry(r.fieldType));
            }
            transExp(d.body);
            env.venv.endScope();
        }
        return null;
    }

    Exp transDec(Absyn.VarDec d) {
        if (env.venv.isRedefinition(d.name)) {
            error(d.pos, "variable redefinition of '" + d.name + "'");
        } else {
            ExpTy et = transExp(d.init);
            // Short forma dec
            if (d.typ == null)
                env.venv.put(d.name, new VarEntry(et.ty));
            else {  // Long form dec
                Types.Type ty = transTy(d.typ);
                if (et.ty.coerceTo(ty))
                    env.venv.put(d.name, new VarEntry(ty));
                else {
                    error(d.pos, "init exp type incompatible");
                    env.venv.put(d.name, new VarEntry(ty.actual()));
                }
            }
        }
        return null;
    }

    Exp transDec(Absyn.TypeDec d) {
        Absyn.TypeDec p, pre = null;
        for (p = d; p != null; p = p.next) {
            if (env.tenv.isRedefinition(p.name)) {
                error(p.pos, "type redefinition of '" + p.name + "'");
                pre.next = p.next; // Skip this redefinition
            } else {
                pre = p;
                env.tenv.put(p.name, new Types.NAME(p.name));
            }
        }
        for (p = d; p != null; p = p.next) {
            ((Types.NAME)env.tenv.get(p.name)).bind(transTy(p.ty));
        }
        for (p = d; p != null; p = p.next) {
            Types.NAME t = (Types.NAME) env.tenv.get(p.name);
            if (t.isLoop()) {
                error(p.pos, "illegal cycle definition: " + p.name);
                env.tenv.set(p.name, null);
            }
        }
        return null;
    }

    Types.Type transTy(Absyn.Ty t) {
        if (t instanceof Absyn.NameTy)
            return transTy((Absyn.NameTy)t);
        if (t instanceof Absyn.RecordTy)
            return transTy((Absyn.RecordTy) t);
        if (t instanceof Absyn.ArrayTy)
            return transTy((Absyn.ArrayTy) t);
        throw new Error("transTy");
    }

    Types.Type transTy(Absyn.NameTy t) {
        if (t == null)
            return new Types.VOID();
        
        Types.Type ty = (Types.Type) env.tenv.get(t.name);
        if (ty == null) {
            error(t.pos, "undefined type: " + t.name);
            return new Types.INT();
        }
        return ty;
    }

    Types.Type transTy(Absyn.RecordTy t) {
        return transTypeFields(t.fields);
    }

    Types.Type transTy(Absyn.ArrayTy t) {
        Types.Type ty = (Types.Type) env.tenv.get(t.typ);
        if (ty == null) {
            error(t.pos, "undefined type");
            return new Types.ARRAY(new Types.INT());
        }
        return new Types.ARRAY(ty);
    }
    
    Types.RECORD transTypeFields(Absyn.FieldList fl) {
        if (fl == null)
            return null;
        
        Types.Type t = (Types.Type) env.tenv.get(fl.typ);
        if (t == null) {
            error(fl.pos, "undefined type: " + fl.typ);
            t = new Types.INT();
        }
        return new Types.RECORD(fl.name, t,
                                transTypeFields(fl.tail));
    }
    
    Exp checkInt(ExpTy et, int pos) {
        if (! (et.ty instanceof Types.INT))
            error(pos, "integer required");
        return et.exp;
    }
}


class ExpTy {
    Exp exp;
    Types.Type ty;

    ExpTy(Exp e, Types.Type t) {
        exp = e;
        ty = t;
    }
}
