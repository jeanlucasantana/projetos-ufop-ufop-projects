// main_gui.cpp
#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include "Sistema.hpp"

class SistemaGUI : public Gtk::Window {
public:
    SistemaGUI() {
        set_title("Sistema de Controle de Voos");
        set_default_size(450, 400);

        box.set_orientation(Gtk::ORIENTATION_VERTICAL);
        box.set_spacing(10);
        box.set_border_width(15);
        add(box);

        btnCadastrarAeronave.set_label("Cadastrar Aeronave");
        btnCadastrarPiloto.set_label("Cadastrar Piloto");
        btnCadastrarPassageiro.set_label("Cadastrar Passageiro");
        btnCriarVoo.set_label("Criar Voo");
        btnListarVoos.set_label("Listar Voos");
        btnListarPassageiros.set_label("Passageiros de um Voo");
        btnRelatorios.set_label("Relatórios");
        btnSair.set_label("Sair");

        Gtk::Frame* frame = Gtk::make_managed<Gtk::Frame>("Menu Principal");
        frame->add(box);
        frame->override_background_color(Gdk::RGBA("#d6eaf8")); // Cor azul clara

        mainBox.pack_start(*frame);
        mainBox.pack_start(btnSair, Gtk::PACK_SHRINK);
        add(mainBox);

        box.pack_start(btnCadastrarAeronave);
        box.pack_start(btnCadastrarPiloto);
        box.pack_start(btnCadastrarPassageiro);
        box.pack_start(btnCriarVoo);
        box.pack_start(btnListarVoos);
        box.pack_start(btnListarPassageiros);
        box.pack_start(btnRelatorios);

        btnCadastrarAeronave.signal_clicked().connect(sigc::mem_fun(*this, &SistemaGUI::on_cadastrarAeronave));
        btnCadastrarPiloto.signal_clicked().connect(sigc::mem_fun(*this, &SistemaGUI::on_cadastrarPiloto));
        btnCadastrarPassageiro.signal_clicked().connect(sigc::mem_fun(*this, &SistemaGUI::on_cadastrarPassageiro));
        btnCriarVoo.signal_clicked().connect(sigc::mem_fun(*this, &SistemaGUI::on_criarVoo));
        btnListarVoos.signal_clicked().connect(sigc::mem_fun(*this, &SistemaGUI::on_listarVoos));
        btnListarPassageiros.signal_clicked().connect(sigc::mem_fun(*this, &SistemaGUI::on_listarPassageiros));
        btnRelatorios.signal_clicked().connect(sigc::mem_fun(*this, &SistemaGUI::on_relatorios));
        btnSair.signal_clicked().connect(sigc::mem_fun(*this, &SistemaGUI::hide));

        show_all_children();
    }

private:
    Gtk::Box box;
    Gtk::Box mainBox{Gtk::ORIENTATION_VERTICAL};
    Gtk::Button btnCadastrarAeronave, btnCadastrarPiloto, btnCadastrarPassageiro, btnCriarVoo;
    Gtk::Button btnListarVoos, btnListarPassageiros, btnRelatorios, btnSair;
    Sistema sistema;

    void show_message(const std::string& title, const std::string& msg) {
        Gtk::MessageDialog dialog(*this, title);
        dialog.set_secondary_text(msg);
        dialog.run();
    }

    void on_cadastrarAeronave() {
        Gtk::Dialog dialog("Cadastrar Aeronave", *this);
        dialog.add_button("Salvar", Gtk::RESPONSE_OK);
        dialog.add_button("Cancelar", Gtk::RESPONSE_CANCEL);
        Gtk::Box* content = dialog.get_content_area();

        Gtk::Entry codigo, modelo, capacidade, velocidade, autonomia;
        codigo.set_placeholder_text("Código");
        modelo.set_placeholder_text("Modelo");
        capacidade.set_placeholder_text("Capacidade");
        velocidade.set_placeholder_text("Velocidade");
        autonomia.set_placeholder_text("Autonomia");

        content->pack_start(codigo);
        content->pack_start(modelo);
        content->pack_start(capacidade);
        content->pack_start(velocidade);
        content->pack_start(autonomia);
        dialog.show_all();

        if (dialog.run() == Gtk::RESPONSE_OK) {
            try {
                sistema.adicionarAeronave(codigo.get_text(), modelo.get_text(),
                                          std::stoi(capacidade.get_text()),
                                          std::stod(velocidade.get_text()),
                                          std::stod(autonomia.get_text()));
                show_message("Sucesso", "Aeronave cadastrada!");
            } catch (...) {
                show_message("Erro", "Verifique os dados inseridos.");
            }
        }
    }

    void on_cadastrarPiloto() {
        Gtk::Dialog dialog("Cadastrar Piloto", *this);
        dialog.add_button("Salvar", Gtk::RESPONSE_OK);
        dialog.add_button("Cancelar", Gtk::RESPONSE_CANCEL);
        Gtk::Box* content = dialog.get_content_area();

        Gtk::Entry nome, matricula, breve, horas;
        nome.set_placeholder_text("Nome");
        matricula.set_placeholder_text("Matrícula");
        breve.set_placeholder_text("Brevê");
        horas.set_placeholder_text("Horas de Voo");

        content->pack_start(nome);
        content->pack_start(matricula);
        content->pack_start(breve);
        content->pack_start(horas);
        dialog.show_all();

        if (dialog.run() == Gtk::RESPONSE_OK) {
            try {
                sistema.adicionarPiloto(nome.get_text(), matricula.get_text(), breve.get_text(), std::stoi(horas.get_text()));
                show_message("Sucesso", "Piloto cadastrado!");
            } catch (...) {
                show_message("Erro", "Dados inválidos.");
            }
        }
    }

    void on_cadastrarPassageiro() {
        Gtk::Dialog dialog("Cadastrar Passageiro", *this);
        dialog.add_button("Salvar", Gtk::RESPONSE_OK);
        dialog.add_button("Cancelar", Gtk::RESPONSE_CANCEL);
        Gtk::Box* content = dialog.get_content_area();

        Gtk::Entry nome, cpf, bilhete;
        nome.set_placeholder_text("Nome");
        cpf.set_placeholder_text("CPF");
        bilhete.set_placeholder_text("Nº Bilhete");

        content->pack_start(nome);
        content->pack_start(cpf);
        content->pack_start(bilhete);
        dialog.show_all();

        if (dialog.run() == Gtk::RESPONSE_OK) {
            try {
                sistema.adicionarPassageiro(nome.get_text(), cpf.get_text(), bilhete.get_text());
                show_message("Sucesso", "Passageiro cadastrado!");
            } catch (...) {
                show_message("Erro", "Erro ao cadastrar passageiro.");
            }
        }
    }

    void on_criarVoo() {
    Voos* v = Voos::criarVoo();  // uso de input via terminal
    sistema.adicionarVoo(v);     // adiciona ao sistema
    show_message("Sucesso", "Voo criado via terminal!");
}
    void on_listarVoos() {
        auto lista = sistema.obterResumoVoos();
        std::stringstream ss;
        for (auto& l : lista) ss << l << "\n";
        show_message("Voos", ss.str());
    }

    void on_listarPassageiros() {
        Gtk::Entry cod;
        cod.set_placeholder_text("Código do Voo");
        Gtk::Dialog dialog("Passageiros do Voo", *this);
        Gtk::Box* content = dialog.get_content_area();
        content->pack_start(cod);
        dialog.add_button("OK", Gtk::RESPONSE_OK);
        dialog.add_button("Cancelar", Gtk::RESPONSE_CANCEL);
        dialog.show_all();
        if (dialog.run() == Gtk::RESPONSE_OK) {
            std::string resultado = sistema.listarPassageirosDeVoo(cod.get_text());
            show_message("Passageiros", resultado);
        }
    }

    void on_relatorios() {
        show_message("Relatório", sistema.gerarRelatorioTexto());
    }
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.sistemadevoo.gui");
    SistemaGUI janela;
    return app->run(janela);
}
