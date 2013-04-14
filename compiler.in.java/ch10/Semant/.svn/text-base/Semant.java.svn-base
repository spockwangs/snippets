/*
 * Semant.java - Semantic analysis
 *
 * Time-stamp: <2010-07-16 14:56:05 wbb>
 */

package Semant;
import Translate.Exp;
import Symbol.Table;
import Temp.Label;

class Env {
    Table venv;                 // value environment
    Table tenv;                 // type environment
    ErrorMsg.ErrorMsg errorMsg;
    
    Env(ErrorMsg.ErrorMsg err, Translate.Level l) {
        errorMsg = err;
        venv = new Table();
        tenv = new Table();

        /*
         * Initialize the environment.
         */
        
        // print(s: string)
        venv.put(Symbol.Symbol.symbol("print"),
                 new FunEntry(new Types.RECORD(Symbol.Symbol.symbol("s"), new Types.STRING(), null),
                              new Types.VOID(), l, new Temp.Label("print")));

        // flush()
        venv.put(Symbol.Symbol.symbol("flush"),
                 new FunEntry(null, new Types.VOID(), l, new Temp.Label("flush")));

        tenv.put(Symbol.Symbol.symbol("int"), new Types.INT());
        tenv.put(Symbol.Symbol.symbol("string"), new Types.STRING());
    }
}


abstract class Entry { }

class VarEntry extends Entry {
    Types.Type ty;
    Translate.Access access;
    
    VarEntry(Types.Type t, Translate.Access a) {
        ty = t;
        access = a;
    }
}


class FunEntry extends Entry {
    Types.RECORD formals;
    Types.Type result;
    public Translate.Level level;
    public Temp.Label label;

    public FunEntry(Types.RECORD f, Types.Type r, Translate.Level v, Temp.Label l) {
        formals = f;
        result = r;
        level = v;
        label = l;
    }
}


public class Semant {
    Env env;
    Translate.Level level;      // tracking current stack frame
    public int nerrors = 0;     // # of errors
    Translate.Translator translator;
    public Tree.Stm ir_tree;
    
    public Semant(ErrorMsg.ErrorMsg err, Translate.Level l, Translate.Translator t) {
        this(new Env(err, l), l, t);
    }

    Semant(Env e, Translate.Level l, Translate.Translator t) {
        env = e;
        level = l;
        translator = t;
    }

    private void error(int pos, String str) {
        env.errorMsg.error(pos, str);
        nerrors++;
    }

    /**
     * Type-check the exp.
     *
     * @return Translate.Frag linked list
     */
    public Translate.Frag transProg(Absyn.Exp exp) {
        Exp e = transExp(exp, null).exp;
        if (nerrors == 0) {
            translator.functionDec(level, e);
            return translator.getResult();
        }

        throw new Error("Type checking failed");
    }

    ExpTy transVar(Absyn.Var v, Label done) {
        if (v instanceof Absyn.SimpleVar) {
            return transVar((Absyn.SimpleVar) v, done);
        }
        if (v instanceof Absyn.FieldVar) {
            return transVar((Absyn.FieldVar) v, done);
        }
        if (v instanceof Absyn.SubscriptVar) {
            return transVar((Absyn.SubscriptVar) v, done);
        }
        throw new Error("transVar");
    }

    ExpTy transVar(Absyn.SimpleVar v, Label done) {
        Entry x = (Entry) env.venv.get(v.name);
        if (x instanceof VarEntry) {
            VarEntry ent = (VarEntry) x;
            return new ExpTy(translator.simpleVar(ent.access, level), ent.ty.actual());
        } else {
            error(v.pos, "undefined variable: " + v.name);
            return new ExpTy(null, new Types.INT());
        }
    }

    ExpTy transVar(Absyn.FieldVar v, Label done) {
        ExpTy vt = transVar(v.var, done);
        if (vt.ty.actual() instanceof Types.RECORD) {
            Types.RECORD ty = (Types.RECORD) vt.ty.actual();
            for (int idx = 0; ty != null; ty = ty.tail, idx++) {
                if (ty.fieldName == v.field) {
                    return new ExpTy(translator.fieldVar(vt.exp, translator.intExp(idx)), ty.fieldType.actual());
                }
            }
            error(v.pos, "undefined field: " + v.field);
        } else {
            error(v.pos, "record type required");
        }
        return new ExpTy(null, new Types.INT());

    }

    ExpTy transVar(Absyn.SubscriptVar v, Label done) {
        ExpTy vt = transVar(v.var, done);
        if (vt.ty.actual() instanceof Types.ARRAY) {
            ExpTy idx_et = transExp(v.index, done);
            if (! (idx_et.ty instanceof Types.INT)) {
                error(v.pos, "array index should be INTEGER");
                return new ExpTy(null, new Types.INT());
            }
            return new ExpTy(translator.subscriptVar(vt.exp, idx_et.exp), ((Types.ARRAY)vt.ty.actual()).element);
        } else {
            error(v.pos, "not an array");
            return new ExpTy(null, new Types.INT());
        }
    }
    
    ExpTy transExp(Absyn.Exp e, Label done) {
        if (e instanceof Absyn.VarExp) {
            return transExp((Absyn.VarExp) e, done);
        }
        if (e instanceof Absyn.NilExp) {
            return transExp((Absyn.NilExp) e, done);
        }
        if (e instanceof Absyn.IntExp) {
            return transExp((Absyn.IntExp) e, done);
        }
        if (e instanceof Absyn.StringExp) {
            return transExp((Absyn.StringExp) e, done);
        }
        if (e instanceof Absyn.CallExp) {
            return transExp((Absyn.CallExp) e, done);
        }
        if (e instanceof Absyn.OpExp) {
            return transExp((Absyn.OpExp) e, done);
        }
        if (e instanceof Absyn.RecordExp) {
            return transExp((Absyn.RecordExp) e, done);
        }
        if (e instanceof Absyn.SeqExp) {
            return transExp((Absyn.SeqExp) e, done);
        }
        if (e instanceof Absyn.AssignExp) {
            return transExp((Absyn.AssignExp) e, done);
        }
        if (e instanceof Absyn.IfExp) {
            return transExp((Absyn.IfExp) e, done);
        }
        if (e instanceof Absyn.WhileExp) {
            return transExp((Absyn.WhileExp) e, done);
        }
        if (e instanceof Absyn.ForExp) {
            return transExp((Absyn.ForExp) e, done);
        }
        if (e instanceof Absyn.BreakExp) {
            return transExp((Absyn.BreakExp) e, done);
        }
        if (e instanceof Absyn.LetExp) {
            return transExp((Absyn.LetExp) e, done);
        }
        if (e instanceof Absyn.ArrayExp) {
            return transExp((Absyn.ArrayExp) e, done);
        }
        throw new Error("transExp");
    }

    ExpTy transExp(Absyn.VarExp e, Label done) {
        return transVar(e.var, done);
    }

    ExpTy transExp(Absyn.NilExp e, Label done) {
        return new ExpTy(translator.nilExp(), new Types.NIL());
    }

    ExpTy transExp(Absyn.IntExp e, Label done) {
        return new ExpTy(translator.intExp(e.value), new Types.INT());
    }

    ExpTy transExp(Absyn.StringExp e, Label done) {
        return new ExpTy(translator.stringExp(e.value), new Types.STRING());
    }

    ExpTy transExp(Absyn.CallExp e, Label done) {
        Entry x = (Entry) env.venv.get(e.func);
        Translate.ExpList el = new Translate.ExpList();
        
        if (x instanceof FunEntry) {
            FunEntry xx = (FunEntry) x;
            Types.RECORD params = xx.formals;
            Absyn.ExpList args = e.args;
            int n = 0;          // track #parameters

            for (; params != null && args != null;
                 params = params.tail, args = args.tail, n++) {
                ExpTy et = transExp(args.head, done);
                if (!params.fieldType.coerceTo(et.ty)) {
                    String msg = (n+1) + "th argument type incompatible";
                    error(e.pos, msg);
                    return new ExpTy(null, new Types.INT());
                } else {
                    el.push(et.exp);
                }
            }
            if (params != null || args != null) {
                for (; params != null; params = params.tail)
                    n++;
                error(e.pos, "#arguments not matched; " +
                      n + " argument(s) expected");
                return new ExpTy(null, new Types.INT());
            }
            return new ExpTy(translator.callExp(xx.label, xx.level, level, el), xx.result);
        } else {
            error(e.pos, "undefined function: " + e.func);
            return new ExpTy(null, new Types.INT());
        }
    }

    ExpTy transExp(Absyn.OpExp e, Label done) {
        ExpTy left = transExp(e.left, done);
        ExpTy right = transExp(e.right, done);
        switch (e.oper) {
        case Absyn.OpExp.PLUS:
        case Absyn.OpExp.MINUS:
        case Absyn.OpExp.MUL:
        case Absyn.OpExp.DIV:
            checkInt(left, e.left.pos);
            checkInt(right, e.right.pos);
            break;
        case Absyn.OpExp.EQ:
        case Absyn.OpExp.NE:
        case Absyn.OpExp.LT:
        case Absyn.OpExp.LE:
        case Absyn.OpExp.GT:
        case Absyn.OpExp.GE:
            if ((left.ty instanceof Types.INT && right.ty instanceof Types.INT) ||
                (left.ty instanceof Types.STRING && right.ty instanceof Types.STRING)) {
                break;
            } else {
                error(e.pos, "operand not matched");
                break;
            }
        default:
            throw new Error("transOpExp");
        }
        return new ExpTy(translator.opExp(e.oper, left.exp, right.exp), new Types.INT());
    }

    ExpTy transExp(Absyn.RecordExp e, Label done) {
        boolean iserror = false;
        Types.Type ty = ((Types.Type) env.tenv.get(e.typ)).actual();
        Translate.ExpList el = new Translate.ExpList();
        
        if (ty instanceof Types.RECORD) {
            Types.RECORD rd = (Types.RECORD) ty;
            Absyn.FieldExpList fl = e.fields;

            for (Translate.ExpList p; rd != null && fl != null; rd = rd.tail, fl = fl.tail) {
                ExpTy init_et = transExp(fl.init, done);
                Types.Type init_ty = init_et.ty;
                if ((fl.name == rd.fieldName) &&
                    ((rd.fieldType.coerceTo(init_ty)) ||
                     init_ty instanceof Types.NIL)) {
                    el.push(init_et.exp);
                } else {
                    error(fl.pos, "undefined field: " + fl.name +
                          "; '" + rd.fieldName + "' expected");
                    iserror = true;
                }
            }
            if (rd != null || fl != null) {
                error(e.pos, "# fields not matched");
                iserror = true;
            }

        } else {
            error(e.pos, "record type required");
            iserror = true;
        }
        if (iserror)
            return new ExpTy(null, new Types.RECORD(e.typ, null, null));
        else
            return new ExpTy(translator.recordExp(el), (Types.RECORD) ty);
    }

    ExpTy transExp(Absyn.SeqExp e, Label done) {
        Absyn.ExpList el = e.list;
        Translate.ExpList tel = new Translate.ExpList();
        ExpTy et = null;

        while (el != null) {
            et = transExp(el.head, done);
            el = el.tail;
            tel.push(et.exp);
        }

        // SeqExp is void
        if (et == null || et.ty instanceof Types.VOID) {
            return new ExpTy(translator.seqExp(tel), new Types.VOID());
        } else {                // SeqExp not void
            return new ExpTy(translator.eseqExp(tel), et.ty);
        }
    }

    ExpTy transExp(Absyn.AssignExp e, Label done) {
        ExpTy var_et = transVar(e.var, done);
        ExpTy exp_et = transExp(e.exp, done);
        if (exp_et.ty.coerceTo(var_et.ty))
            return new ExpTy(translator.assignExp(var_et.exp, exp_et.exp), new Types.VOID());
        else {
            error(e.pos, "type not matched");
            return new ExpTy(null, exp_et.ty);
        }
    }

    ExpTy transExp(Absyn.IfExp e, Label done) {
        ExpTy et1 = transExp(e.test, done);

        if (! (et1.ty instanceof Types.INT))
            error(e.test.pos, "integer required");

        ExpTy et2 = transExp(e.thenclause, done);
        ExpTy et3 = null;

        if (e.elseclause != null)
            et3 = transExp(e.elseclause, done);
        if (et3 != null && ! et2.ty.coerceTo(et3.ty) && ! et3.ty.coerceTo(et2.ty))
            error(e.pos, "type of thenclause and elseclause not matched");
        if (et3 == null)
            return new ExpTy(translator.ifExp(et1.exp, et2.exp, null), new Types.VOID());
        else
            return new ExpTy(translator.ifExp(et1.exp, et2.exp, et3.exp), et2.ty);
    }

    ExpTy transExp(Absyn.WhileExp e, Label done) {
        ExpTy et1 = transExp(e.test, done);
        Label new_done = new Label();
        
        ExpTy et2 = transExp(e.body, new_done);

        if (! (et1.ty instanceof Types.INT))
            error(e.test.pos, "integer required");
        if (! (et2.ty instanceof Types.VOID))
            error(e.body.pos, "void type required");

        return new ExpTy(translator.whileExp(et1.exp, et2.exp, new_done), new Types.VOID());
    }

    ExpTy transExp(Absyn.ForExp e, Label done) {
        env.venv.beginScope();
        
        Exp dec_exp = transDec(e.var);

        ExpTy hi_et = transExp(e.hi, done);
        VarEntry vent = (VarEntry) env.venv.get(e.var.name);
        if (! hi_et.ty.coerceTo(vent.ty))
            error(e.hi.pos, "type not matched");

        Label new_done = new Label();
        ExpTy body_et = transExp(e.body, new_done);

        if (! (body_et.ty instanceof Types.VOID))
            error(e.body.pos, "VOID type required for for expression");

        env.venv.endScope();

        /*
         * Convert for-exp to let-exp to make translation more easily.
         */
        
        Symbol.Symbol i, limit;
        Absyn.DecList let_decs;
        Absyn.SimpleVar i_var, limit_var;
        Absyn.OpExp cmp1, cmp2;
        Absyn.WhileExp while_exp;
        Absyn.Exp let_body;
        Absyn.ExpList el;
        Absyn.LetExp let_exp;
        
        i = e.var.name;
        limit = Symbol.Symbol.symbol("$limit"); // this name not occur in
                                             // original source program
        // var i:= lo
        // var $limit := hi
        let_decs = new Absyn.DecList(e.var,
                                     new Absyn.DecList(new Absyn.VarDec(-1, limit, null, e.hi), null));

        i_var = new Absyn.SimpleVar(-1, i);
        limit_var = new Absyn.SimpleVar(-1, limit);
        cmp1 = new Absyn.OpExp(-1, new Absyn.VarExp(-1, i_var), Absyn.OpExp.GE, new Absyn.VarExp(-1, limit_var));
        cmp2 = new Absyn.OpExp(-1, new Absyn.VarExp(-1, i_var), Absyn.OpExp.LE, new Absyn.VarExp(-1, limit_var)); 

        // Explist in the while exp.
        Absyn.IntExp one = new Absyn.IntExp(-1, 1);
        Absyn.AssignExp inc_one = new Absyn.AssignExp(-1, i_var, new Absyn.OpExp(-1, new Absyn.VarExp(-1, i_var), Absyn.OpExp.PLUS, one));
        el = new Absyn.ExpList(e.body,
                               new Absyn.ExpList(new Absyn.IfExp(-1, cmp1, new Absyn.BreakExp(-1)),
                                                 new Absyn.ExpList(inc_one, null)));

        while_exp = new Absyn.WhileExp(-1, one, new Absyn.SeqExp(-1, el));
        let_body = new Absyn.IfExp(-1, cmp2, while_exp);
        let_exp = new Absyn.LetExp(-1, let_decs, let_body);
        return transExp(let_exp, done);
    }

    /**
     * Check and translate break-exp.
     *
     * The parameter 'done' has 2 uses: the done label of the enclosing
     * iteration expression and it can be used to check the validity of
     * break-exp.  If done is non-null then it must be enclosed in a
     * iteration exp.
     */
    ExpTy transExp(Absyn.BreakExp e, Label done) {
        if (done == null)
            error(e.pos, "invalid break-exp; not in a for-exp or while-exp");
        return new ExpTy(translator.breakExp(done), new Types.VOID());
    }

    ExpTy transExp(Absyn.LetExp e, Label done) {
        env.venv.beginScope();
        env.tenv.beginScope();

        Translate.ExpList el = new Translate.ExpList();
        for (Absyn.DecList p = e.decs; p != null; p = p.tail)
            el.push(transDec(p.head));

        ExpTy et = transExp(e.body, done);

        env.venv.endScope();
        env.tenv.endScope();

        return new ExpTy(translator.letExp(el, et.exp), et.ty);
    }

    ExpTy transExp(Absyn.ArrayExp e, Label done) {
        boolean iserror = false;

        // Check the array type.
        Types.Type ty = (Types.Type) env.tenv.get(e.typ);
        Types.ARRAY array_ty;
        if (ty == null) {
            error(e.pos, "undefined array type: " + e.typ);
            iserror = true;
        }
        if (! (ty.actual() instanceof Types.ARRAY)) {
            error(e.pos, "ARRAY required");
            iserror = true;
        }
        array_ty = (Types.ARRAY) ty.actual();

        // Check the size exp.
        ExpTy size_et = transExp(e.size, done);
        if (! (size_et.ty instanceof Types.INT)) {
            error(e.size.pos, "integer required");
            iserror = true;
        }

        // Check the init exp.
        ExpTy init_et = transExp(e.init, done);
        if (! init_et.ty.coerceTo(array_ty.element)) {
            error(e.init.pos, "incompatible with array type");
            iserror = true;
        }

        if (iserror) {
            return new ExpTy(null, new Types.ARRAY(new Types.INT()));
        } else {
            return new ExpTy(translator.arrayExp(size_et.exp, init_et.exp), array_ty);
        }
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
        boolean iserror = false;
        
        // Check each function dec (the signature) and enter them into the env.
        for (Absyn.FunctionDec p = d, pre = null; p != null; p = p.next) {
            if (env.venv.isRedefinition(p.name)) {
                error(p.pos, "function redefinition of '" + p.name + "'");
                pre.next = p.next; // skip this redefinition
                iserror = true;
            } else {
                Types.Type result = transTy(p.result);
                Types.RECORD formals = transTypeFields(p.params);
                env.venv.put(p.name, new FunEntry(formals, result, level, new Label(p.name)));
                pre = p;
            }
        }

        // Check each function dec again.  This time check the body.
        for (; d != null; d = d.next) {

            // Bind the formal parameters.
            Types.RECORD r = transTypeFields(d.params);
            Util.BoolList bl = null;
            for (Absyn.FieldList p = d.params; p != null; p = p.tail) {
                bl = new Util.BoolList(true, bl);
            }
            Translate.Level newlevel = new Translate.Level(level, d.name, bl);
            env.venv.beginScope();
            for (int i = 1; r != null; r = r.tail, i++) {
                env.venv.put(r.fieldName,
                             new VarEntry(r.fieldType, newlevel.accessParam(i)));
            }

            // Check the function body in a new semantic env.

            Semant newsem = new Semant(env, newlevel, translator);
            ExpTy fun_et = newsem.transExp(d.body, null);
            nerrors += newsem.nerrors;

            // Check the return type of this funciton.
            if (! fun_et.ty.coerceTo(transTy(d.result))) {
                // NOTE: d.result may be null which means return type is void.
                if (d.result == null)
                    error(d.pos, "return type should be void");
                else
                    error(d.result.pos, "incompatible with return type");
                iserror = true;
            }
            env.venv.endScope();
            translator.functionDec(newlevel, fun_et.exp);
        }
        if (iserror)
            return null;
        else
            return null;
    }

    Exp transDec(Absyn.VarDec d) {
        if (env.venv.isRedefinition(d.name)) {
            error(d.pos, "variable redefinition of '" + d.name + "'");
            return null;
        } 

        ExpTy et = transExp(d.init, null);
        Translate.Access a = level.allocLocal(true);
            
        // Short forma dec
        if (d.typ == null)
            env.venv.put(d.name, new VarEntry(et.ty, a));
        else {  // Long form dec
            Types.Type ty = transTy(d.typ);
            if (et.ty.coerceTo(ty))
                env.venv.put(d.name, new VarEntry(ty, a));
            else {
                error(d.pos, "init exp type incompatible");
                env.venv.put(d.name, new VarEntry(ty, a));
                return null;
            }
        }

        return translator.varDec(a, level, et.exp);
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
        return translator.typeDec();
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
